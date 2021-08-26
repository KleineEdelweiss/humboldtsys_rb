# lib/humboltsys/syscore.rb

# Require the loaded SysCore module
require_relative "ext"

##
# Append methods to SysCore
module SysCore
  ##
  # Return the uptime of the machine
  # as a hash of the different time components
  def self.uptime_f
    ##
    # The second value, :idle, leads to much
    # higher values than the actual uptime --
    # :up is the value that most people need.
    sec_to_time SysCore.uptime[:up]
  end # End uptime
  
  ##
  # Auxiliary method to convert an int delta
  # of seconds to a readable time
  def self.sec_to_time(seconds)
    mins, s = seconds.divmod 60
    hours, m = mins.divmod 60
    days, h = hours.divmod 24
    w, d = days.divmod 7
    
    {weeks: w, days: d, hours: h, minutes: m, seconds: s}
  end # End sec_to_time
end # End method appendment