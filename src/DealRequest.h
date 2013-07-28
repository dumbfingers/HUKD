/*
 * DealRequest.h
 *
 *  Created on: Jul 28, 2013
 *      Author: allen
 */

#ifndef DEALREQUEST_H_
#define DEALREQUEST_H_

#include <QtCore/QObject>

class DealRequest {
public:
	DealRequest();
	virtual ~DealRequest();

    /*
     * Makes a network call to retrieve the twitter feed for the specified screen name
     * @param screenName - the screen name of the feed to extract
     * @see onTimelineReply
     */
    void requestDeal();
Q_SIGNALS:
	/*
	 * This signal is emitted when the twitter request is received
	 * @param info - on success, this is the json reply from the request
	 *               on failure, it is an error string
	 * @param success - true if twitter request succeed, false if not
	 */
	void complete(const QString &info, bool success);
private Q_SLOTS:
	/*
	 * Callback handler for QNetworkReply finished() signal
	 */
	void onDealReply();
};

#endif /* DEALREQUEST_H_ */
