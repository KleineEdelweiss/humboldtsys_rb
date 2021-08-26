# lib/humboldtsys/cosntants.rb

##
# Global constants for HumboldtSys
module HumboltSys
  ##
  # Numeric constants
  KILO = 10**3
  KIBI = 2**10
  MEGA = KILO * KILO
  MEBI = KIBI * KIBI
  TERA = KILO * MEGA
  TEBI = KIBI * MEBI
  PETA = KILO * TERA
  PEBI = KILO * TEBI
  
  # Hardware
  HWMON = "/sys/class/hwmon"
  CPU = {base: "/proc/cpuinfo", kernel: "/proc/stat"}
  
  # Host data
  KERNEL = "/proc/sys/kernel"
  RELEASE = "/etc/os-release"
  
  HOST = {
    # Kernel Data
    k_name: "#{KERNEL}/ostype", 
    k_release: "#{KERNEL}/osrelease",
  }
end # End constant