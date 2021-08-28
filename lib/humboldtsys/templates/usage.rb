# lib/humboldtsys/templates/usage.rb

# Include error messages
require_relative "generic"

##
# Wrap this inside HumboldtSys
module HumboldtSys
  ##
  # Inclusion module to support basic operations on
  # an object type that should be able to support
  # calculable usage data about itself
  module Usage
    ##
    # Add generic functionality
    include Genera
    
    ##
    # Overrideable methods
    
    # Reference value, from which usage is determined
    def my_ref() err_ni(__method__) end
    
    # Current usage of the object's available units
    def my_used() err_ni(__method__) end
    
    # Currently unused portion of the object's units
    def my_unused() err_ni(__method__) end
  end # End Usage module
end # End HS wrap