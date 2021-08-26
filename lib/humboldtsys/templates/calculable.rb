# lib/humboldtsys/templates/calculable.rb

##
# Inclusion module to support basic operations on
# an object type that should be able to support
# calculable / statable data about itself
module Calculable
  # Raw maximum / total available of usable units
  def total() raise NotImplementedError end
  
  # Current usage of the object's available units
  def unavailable() raise NotImplementedError end
  
  # Currently unused portion of the object's units
  def available() raise NotImplementedError end
  
  ##
  # Overrideable methods
end # End Calculable module