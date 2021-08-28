# lib/humboldtsys/cpu.rb

# Regular requires
require_relative "constants"
require_relative "templates/currently"
require_relative "templates/usage"

# Require Extensions
require_relative "syscore"

##
# Wrap inside of the main
module HumboldtSys
  ##
  # This module handles monitoring of the CPUs on the
  # host system.
  module Processor
    ##
    # Class to cache all core data
    class ProcCache
      ##
      # Keep data current, cached
      include Currently
      
      ##
      # Initialize this with and update
      def initialize() update end
      
      ##
      # Return the average system usage
      def avg() Core.new(current[-1]) end
      
      ##
      # Return the processor usage for a specific
      # logical unit.
      def get(index: -1) Core.new(current[index.to_i]) end
      
      ##
      # Update the :current value by statting the proc
      # data -- /proc/stat (and core information
      def specific_update() SysCore.pstat end
      
      ##
      # Private data and methods
      private
      
      ##
      # Single processor unit struct type
      Core = Struct.new(:user, :nice, :system, :idle,
        :iowait, :irq, :softirq, :steal, :guest, :guest_nice,
        keyword_init: true) do
          
      end # End struct for simple Core object
    end # End procs cache module
  end # End Processor module
end # End HS wrapper