# lib/humboldtsys/templates/generic.rb

##
# This module contains several generic operations that most
# items in this library should perform.
module HumboldtSys
  ##
  # Generic operations
  module Genera
    ##
    # Custom method not implemented error with more data
    def err_ni(method: ) raise "::ERROR:: Must implement #{method}" end
  end # End Genera
end # End wrap in HS