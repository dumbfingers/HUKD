#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QtCore/QObject>

namespace bb {
namespace cascades {
class Application;
class LocaleHandler;
}
}

class QTranslator;

class DealDataModel;
class DealRetriever;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI: public QObject {
Q_OBJECT

public:
	ApplicationUI(bb::cascades::Application *app);
	virtual ~ApplicationUI() {
	}

	Q_PROPERTY(DealDataModel *dataModel READ dataModel CONSTANT)
	;

	DealDataModel *dataModel();Q_INVOKABLE
	void updateDataModel(bool silent = false);

public Q_SLOTS:

	/*
	 * Allows the QML to reset the state of the application
	 */
	void reset();

signals:
	void networkChanged();

private slots:
	void onSystemLanguageChanged();

	void onNetworkStatusChanged(bool connected);

private:
	QTranslator* m_pTranslator;
	bb::cascades::LocaleHandler* m_pLocaleHandler;

	DealDataModel *_dataModel;
	DealRetriever *_dealRetriever;
};

#endif /* ApplicationUI_HPP_ */
