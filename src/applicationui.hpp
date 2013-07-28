#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <bb/cascades/GroupDataModel>

namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
    }
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() { }

public Q_SLOTS:
    /*
     * Called by the QML to get deals list
     */
    void requestDeals();
    /*
     * Allows the QML to reset the state of the application
     */
    void reset();

Q_SIGNALS:
	/*
	 * This signal is emitted whenever the deals have been loaded successfully
	 */
	void dealsLoaded();

	/*
	 * The change notification signals of the properties
	 */
	void activeChanged();
	void statusChanged();

private Q_SLOTS:
	/*
	 * Handles the complete signal from TwitterRequest when
	 * the request is complete
	 * @see DealRequest::complete()
	 */
	void onDeal(const QString &info, bool success);

private slots:
    void onSystemLanguageChanged();

private:
    /*
     * Parses the JSON response from the twitter request
     */
    void parseResponse(const QString&);

    /*
     * The accessor methods of the properties
     */
    bool active() const;
    bool error() const;
    QString errorMessage() const;
    bb::cascades::DataModel* model() const;

private:
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    bool m_active;
    bool m_error;
    QString m_errorMessage;
    bb::cascades::GroupDataModel* m_model;
};

#endif /* ApplicationUI_HPP_ */
