require "rake/extensiontask"

# Build the host_data extension, that is used to
# access host system data fields.
Rake::ExtensionTask.new "host_data" do |ext|
  ext.lib_dir = "lib/share/host_data"
end

# Build the "other" extension, which contains general,
# uncategorized functions
Rake::ExtensionTask.new "other" do |ext|
  ext.lib_dir = "lib/share/other"
end