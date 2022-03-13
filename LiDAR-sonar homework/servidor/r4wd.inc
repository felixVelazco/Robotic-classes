# Desc: Device definitions for Activemedia robots.
# Author: Richard Vaughan, Andrew Howard,  Luis Riazuelo
# Date: 10 Jun 2002
# CVS: $Id: pioneer.inc,v 1.30 2008-01-15 01:25:42 rtv Exp $

# The Pioneer2DX sonar array

#  prototype for p2dx sonar sensors

define juancho position
(
	#shape of juancho
	polygons 1
	polygon[0].points 4
	polygon[0].point[0] [0 0.05]
	polygon[0].point[0] [0 0.25]	
	polygon[0].point[0] [0.4 0.25]
	polygon[0].point[0] [0.2 0.05]
)
