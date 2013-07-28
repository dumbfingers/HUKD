#include "applicationui.hpp"
#include "DealRequest.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

#include <bb/data/JsonDataAccess>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
, m_active(false)
, m_error(false)
, m_model(new GroupDataModel(QStringList() << "title", this))
{
	m_model->setGrouping(ItemGrouping::None);

    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
    if(!QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()))) {
        // This is an abnormal situation! Something went wrong!
        // Add own code to recover here
        qWarning() << "Recovering from a failed connect()";
    }
    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("hukd", this);
    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("HUKD_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit statusChanged();
}

void ApplicationUI::requestDeals()
{
	if (m_active)
		return;
	DealRequest* request = new DealRequest(this);
	connect(request, SIGNAL(complete(QString, bool)), this, SLOT(onDeal(QString, bool)));

	request->requestDeal();
	m_active = true;
	emit activeChanged();
}

void ApplicationUI::onDeal(const QString &info, bool success)
{
	DealRequest* request = qobject_cast<DealRequest*>(sender());

	if (success) {
		parseResponse(info);

		emit dealsLoaded();
	} else {
		m_errorMessage = info;
		m_error = true;
		emit statusChanged();
	}

	m_active = false;
	emit activeChanged();

	request->deleteLater();
}

void ApplicationUI::parseResponse(const QString &response)
{
	m_model->clear();

	if (response.trimmed().isEmpty())
		return;

	JsonDataAccess dataAccess;
	const QVariant variant = dataAccess.loadFromBuffer(response);

	const QVariantList feed = variant.toList();

	foreach (const QVariant &deal, feed) {
		m_model->insert(deal.toMap());
	}
}

bool ApplicationUI::active() const
{
    return m_active;
}

bool ApplicationUI::error() const
{
    return m_error;
}

QString ApplicationUI::errorMessage() const
{
    return m_errorMessage;
}

bb::cascades::DataModel* ApplicationUI::model() const
{
    return m_model;
}
