# lib/humboldtsys/cosntants.rb

# Global constants for HumboldtSys
module Constants
  # Hardware
  HWMON = "/sys/class/hwmon"
  CPU = {base: "/proc/cpuinfo", kernel: "/proc/stat"}
  RAM = "/proc/meminfo"
  
  # Host data
  UPTIME = "/proc/uptime"
  KERNEL = "/proc/sys/kernel"
  HOST = {
    name: "#{KERNEL}/ostype", 
    release: "#{KERNEL}/osrelease",
    hostname: "#{KERNEL}/hostname",
    domain: "#{KERNEL}/domainname",
    distro: "#{KERNEL}/version",
  }
end