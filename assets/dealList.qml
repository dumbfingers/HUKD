import bb.cascades 1.0

Page {
    Container {
        layout: DockLayout {}
        
        //! [0]
        ListView {
            dataModel: _timeline.model
            
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
        //! [0]
    }
}
