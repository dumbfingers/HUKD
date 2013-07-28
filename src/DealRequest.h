/*
 * DealRequest.h
 *
 *  Created on: Jul 28, 2013
 *      Author: allen
 */

#ifndef DEALREQUEST_H_
#define DEALREQUEST_H_

#include <QtCore/QObject>
#include <bb/cascades/GroupDataModel>

class DealRequest {
public:
	DealRequest();
	virtual ~DealRequest();
public Q_SLOTS:
	/*
	 * Called by the QML to get deals list
	 */
	void requestDeals();
};

#endif /* DEALREQUEST_H_ */
