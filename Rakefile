# Rakefile
require "rake/extensiontask"

# Build the host_data extension, that is used to
# access host system data fields.
Rake::ExtensionTask.new "host_data" do |ext|
  ext.lib_dir = "lib/share/host_data"
  ext.source_pattern = "*.{c,h}"
end # End host data extension

# Build the SysCore extension, that is used to
# access CPU, RAM, and various proc info
Rake::ExtensionTask.new "syscore" do |ext|
  ext.lib_dir = "lib/share/syscore"
  ext.source_pattern = "*.{c,h}"
end # End SysCore extension

# Build the "other" extension, which contains general,
# uncategorized functions
Rake::ExtensionTask.new "other" do |ext|
  ext.lib_dir = "lib/share/other"
  ext.source_pattern = "*.{c,h}"
end # End other extension