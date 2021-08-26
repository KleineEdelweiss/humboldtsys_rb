# lib/humboldtsys/memory.rb

# Local requires
require_relative "constants"
require_relative "templates/currently"
require_relative "syscore"

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
    # Constructor
    def initialize() update end
    
    ##
    # Total memory of this type
    def total() current[:total] end
    
    ##
    # Free memory of this type
    def free() raise "::ERROR:: Must implement #{__method__}" end
    
    # Used
    def used() raise "::ERROR:: Must implement #{__method__}" end
  end # End memory abstraction
  
  ##
  # Class to store system memory information
  class RAM < AbsMemory
    ##
    # Available / Free RAM
    def free() current[:avail] end
    
    ##
    # Used RAM
    def used() (total - free) end
    
    ##
    # Specific way to update the data
    def specific_update() SysCore.mem end
  end # End concrete RAM class
  
  ##
  # Class to store system SWAP information
  class SWAP < AbsMemory
    ##
    # Available / Free RAM
    def free() current[:free] end
    
    ##
    # Used RAM
    def used() (total - free) end
    
    ##
    # Specific way to update the data
    def specific_update() SysCore.swap end
  end # End concrete SWAP class
end # End memory module