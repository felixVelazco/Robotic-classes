
define sicklaser ranger
(
	sensor( 			
  # laser-specific properties
  # factory settings for LMS200	
  range [ 0  5.0 ]
  fov 270.0
  #fov 180.0
  samples 772
  )
  # generic model properties
  color "red"
  size [ 0.07 0.07 0.05 ] # dimensions from LMS200 data sheet	
)

