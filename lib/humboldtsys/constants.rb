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
  RELEASE = "/etc/os-release"
  
  HOST = {
    # Kernel Data
    k_name: "#{KERNEL}/ostype", 
    k_release: "#{KERNEL}/osrelease",
    
    # Kernel-loaded network data
    hostname: "#{KERNEL}/hostname",
    domain: "#{KERNEL}/domainname",
  }
end