# frozen_string_literal: true
require_relative "lib/humboldtsys/version.rb"

# Spec
Gem::Specification.new do |spec|
  spec.name = "humboldtsys"
  spec.version = HumboldtSys::VERSION
  spec.summary = "Genericized Linux system access interface"
  spec.description = <<~DESC
    Ruby module to provide access to Linux system information.
    This contains genericized access to data that will be used
    in related projects, and I will be refactoring some of them
    to depend on this one.
    
    This interface will also check for external programs that may
    be necessary for certain operations.
  DESC
  spec.authors = ["Edelweiss"]
  
  # Website data
  spec.homepage = "https://github.com/KleineEdelweiss/humboldtsys_rb"
  spec.licenses = ["LGPL-3.0"]
  spec.metadata = {
    "homepage_uri"        => spec.homepage,
    "source_code_uri"     => "https://github.com/KleineEdelweiss/humboldtsys_rb",
    #"documentation_uri"   => "",
    #"changelog_uri"       => "https://github.com/KleineEdelweiss/humboldtsys_rb/blob/master/CHANGELOG.md",
    "bug_tracker_uri"     => "https://github.com/KleineEdelweiss/humboldtsys_rb/issues"
  }
  
  # List of files
  spec.files = Dir.glob("lib/**/*")
  
  # Rdoc options
  spec.extra_rdoc_files = Dir["README.md", "CHANGELOG.md", "LICENSE.txt"]
  spec.rdoc_options += [
    "--title", "HumboldtSys RB -- Generic Linux system access interface in Ruby",
    "--main", "README.md",
    "--line-numbers",
    "--inline-source",
    "--quiet"
  ]
  
  # Minimum Ruby version
  spec.required_ruby_version = ">= 2.7.0"
  
  # Compiled extensions
  spec.extensions = ['ext/syscore/extconf.rb',]
end # End spec