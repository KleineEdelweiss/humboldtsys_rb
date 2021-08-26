# lib/humboldtsys/host.rb

# Regular requires
require_relative "./constants"

# Require Extensions
require_relative "../syscore/syscore"

# This module will provide generic access to host system
# information and settings.
module HumboldtSys
  module Host
    ##
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
          distro: release_info(File.read(HumboldtSys::RELEASE).split("\n")),
          kernel: SysCore.uname,
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
      def hostname() SysCore.hostname end
        
      # Return just the domain name
      def domain() SysCore.domainname end
    end # End Host class
  end # End Host module
end