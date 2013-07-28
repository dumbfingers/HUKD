import bb.cascades 1.0

TabbedPane {
    showTabsOnActionBar: true
    Tab { //First tab
        // Localized text with the dynamic translation and locale updates support
        title: qsTr("Deals") + Retranslate.onLocaleOrLanguageChanged
        onTriggered: {
            hukd.requestDeals();
        }
        Page {
            Container {
                //! [0]
                ListView {
                    dataModel: hukd.model
                    
                    listItemComponents: [
                        ListItemComponent {
                            type: "item"
                            StandardListItem {
                                status: ListItemData.created_at
                                description: ListItemData.text
                                imageSpaceReserved: false
                            }
                        }
                    ]
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
