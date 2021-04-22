# lib/humboldtsys/sysfs.rb

require_relative "./constants"

# This module will provide access to the sysfs
# virtual filesystem, including (and primarily for
# the initial case in writing this) system hardware.
module SysFS
  # Enumerate devices in hwmon
  # to be processed in the calling code.
  # 
  # This will provide a basic way to access and
  # cross-reference the device with other data,
  # by listing the device's SysFS index, path, and
  # (if available) driver info, bus info, modalias,
  # vendor and device IDs, PCI classes, etc.
  # 
  # Not all devices will list all fields. Some may have
  # an empty uevent, so it may need separate parsing
  # solutions.
  # 
  # For example, my iwlwifi card does NOT fill
  # in the uevent, but it DOES have a '/device/type' file,
  # which says it's "iwlwifi". This file, however, is NOT
  # present on ANY of my other devices, so it probably should
  # not be considered a standard device file, whereas "/device/uevent"
  # IS present on all of them, even if empty.
  # 
  # All devices will return at least an index and directory, however,
  # so odd cards can still be processed by separate code.
  def self.enumerate
    Dir.glob("#{Constants::HWMON}/*").collect do |device|
      {index: device.split("/").last, path: "#{device}"}
    end.collect { |device| # Add in the uevent data
      device.update(self.uevent(File.read("#{device[:path]}/device/uevent"))) }
  end # End enumerate
  
  # Split uevent data into key-value pairs
  def self.uevent(ue)
    ue.split("\n").collect do |line|
      line.split("=", 2).then { |k,v| {k.strip.downcase.to_sym => v.strip.downcase} }
    end.reduce(Hash.new, :update).then { |fields| {uevent: fields} }
  end # End uevent splitter
end # End SysFS module