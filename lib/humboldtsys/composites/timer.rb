# lib/humboldtsys/composites/timer.rb

##
# Timers contains a system object that can be used
# to update things, if it is no longer in use.
# 
# "In use" is define by the delay and if the current time
# exceeds the last known update time.
module Timers
  ##
  # Timer object class
  class Timer
    # Milliseconds for timer
    attr_reader :msec
    # Last time used
    attr_reader :last
    
    ##
    # Constructor -- sets the MS delay, runs update
    def initialize(msec: 250)
      set(msec: msec)
      update
    end # End constructor
    
    ##
    # Set a new ms delay
    def set(msec: ) @msec = msec end
    
    ##
    # Update the last time to the current time
    def update() @last = Time.now end
    
    ##
    # Check if the timer is available
    def available?
      current = Time.now
      cfix = current.to_f
      lfix = last.to_f
      ((cfix - lfix) * 1000) >= msec
    end # End available?
  end # End Timer class
end # End Timers module