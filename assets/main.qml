import bb.cascades 1.0

TabbedPane {
    showTabsOnActionBar: true
    Tab { //First tab
        // Localized text with the dynamic translation and locale updates support
        title: qsTr("Deals") + Retranslate.onLocaleOrLanguageChanged
        onTriggered: {
            
        }
        Page {
            Container {
                Label {
                    text: qsTr("First tab") + Retranslate.onLocaleOrLanguageChanged
                }
            }
        }
    } //End of first tab
    Tab { //Second tab
        title: qsTr("Tab 2") + Retranslate.onLocaleOrLanguageChanged
        Page {
            Container {
                Label {
                    text: qsTr("Second tab") + Retranslate.onLocaleOrLanguageChanged
                }
            }
        }
    } //End of second tab
}
