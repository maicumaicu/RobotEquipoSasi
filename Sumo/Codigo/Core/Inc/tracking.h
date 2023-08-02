/*
 * tracking.h
 *
 *  Created on: Jul 25, 2023
 *      Author: jore
 */

#ifndef INC_TRACKING_H_
#define INC_TRACKING_H_

int targetPosition (int * mediciones);
void targetTracking(int position);
int linePosition(int * medicion);
void lineTracking(int position);


#define MAXVELOCITY 65535
#define MINVELOCITY 40000
#endif /* INC_TRACKING_H_ */
