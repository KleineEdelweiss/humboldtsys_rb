# Rakefile
require "rake/extensiontask"

# Build the SysCore extension
Rake::ExtensionTask.new "syscore" do |ext|
  ext.lib_dir = "lib/syscore"
  ext.source_pattern = "*.{c,cpp,h,hpp}"
end # End SysCore extension