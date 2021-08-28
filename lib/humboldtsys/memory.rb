# lib/humboldtsys/memory.rb

# Local requires
require_relative "constants"
require_relative "syscore"
require_relative "templates/currently"
require_relative "templates/usage"

##
# Wrap memory inside of HS
module HumboldtSys
  ##
  # Memory module -- needs abstraction
  module Memory
    ##
    # Abstract memory class
    class AbsMemory
      ##
      # Keep data current, cached
      include Currently
      
      ##
      # Require some method of calculating usage
      include Usage
      
      ##
      # Constructor
      def initialize() update end
      
      ##
      # Total memory of this type
      def total() my_ref end
      
      ##
      # Free memory of this type
      def free() my_unused end
      
      ##
      # Used memory
      def used() my_used end
        
      protected
      
      ##
      # Total memory
      def my_ref() current[:total] end
    end # End memory abstraction
    
    ##
    # Class to store system memory information
    class RAM < AbsMemory
      ##
      # Available / Free RAM
      def my_unused() current[:avail] end
      
      ##
      # Used RAM
      def my_used() (total - free) end
      
      ##
      # Specific way to update the data
      def specific_update() SysCore.mem end
    end # End concrete RAM class
    
    ##
    # Class to store system SWAP information
    class SWAP < AbsMemory
      ##
      # Available / Free RAM
      def my_unused() current[:free] end
      
      ##
      # Used RAM
      def my_used() (total - free) end
      
      ##
      # Specific way to update the data
      def specific_update() SysCore.swap end
    end # End concrete SWAP class
  end # End memory module
end # End HS wrap