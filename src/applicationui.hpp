#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QtCore/QObject>

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
     * Allows the QML to reset the state of the application
     */
    void reset();

Q_SIGNALS:

private Q_SLOTS:


private slots:
    void onSystemLanguageChanged();

private:
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
};

#endif /* ApplicationUI_HPP_ */
