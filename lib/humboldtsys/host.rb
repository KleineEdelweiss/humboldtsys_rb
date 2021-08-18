# lib/humboldtsys/host.rb

# Regular requires
require_relative "./constants"

# Require Extensions
require_relative "../syscore/syscore"

# This module will provide generic access to host system
# information and settings.
module Host
  # Return the uptime of the machine
  # as a hash of the different time components
  def self.uptime
    # First value is the uptime; second
    # value is idle processor time ACROSS
    # ALL CORES (which can lead much
    # higher numbers, if many cores)
    File.read(Constants::UPTIME).split.first.to_i
      .then { |seconds| sec_to_time(seconds) }
  end # End uptime
  
  # Convert an int number of seconds
  # to a time
  def self.sec_to_time(seconds)
    mins, s = seconds.divmod 60
    hours, m = mins.divmod 60
    days, h = hours.divmod 24
    w, d = days.divmod 7
    
    {weeks: w, days: d, hours: h, minutes: m, seconds: s}
  end
  
  # Get the system time -- this is just
  # the host system's local time.
  def self.time
    Time.now.then do |t|
    { y: t.year, mo: t.mon, d: t.day,
      h: t.hour, min: t.min, s: t.sec,
      z: t.zone, }
    end
  end # End system time
  
  # Class to store system readers
  # and update methods
  class System
    # Basic host system configurations
    # 
    # The OS, architecture, and kernel
    # will not change without a reboot, so
    # they should be considered immutable.
    # 
    # As such, no mechanism is provided to
    # change them without restarting the program
    # or replacing the System object.
    attr_reader :host
    
    # Initialize the distro data and then
    # update the host data with stat.
    def initialize
      @host = {
        distro: release_info(File.read(Constants::RELEASE).split("\n")),
        kernel: HostData.uname,
      }
      stat
    end # End constructor
    
    # Split the data in the `/etc/os-release` file
    # into a key-value pair.
    def release_info(osr)
      osr.collect do |line|
        line.split("=", 2).then do |k,v|
          {k.strip.downcase.to_sym => v.strip.gsub("\"", "")}
        end
      end.reduce Hash.new, :update
    end # End split release
    
    # Return the system information
    # as a hash
    def stat() @host.update({hostname: hostname, domainname: domain}) end
    
    # Return just the hostname
    def hostname() HostData.hostname.strip end
      
    # Return just the domain name
    def domain() HostData.domainname.strip end
  end # End Host class
end # End Host module