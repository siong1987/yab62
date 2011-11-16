# -*- encoding: utf-8 -*-
require File.expand_path('../lib/yab62/version', __FILE__)

Gem::Specification.new do |gem|
  gem.authors       = ["Teng Siong Ong"]
  gem.email         = ["siong1987@gmail.com"]
  gem.description   = %q{Yet another Base62 convertor}
  gem.summary       = %q{What do you expect? This is yet another Base62 convertor written in C extension.}
  gem.homepage      = ""
  gem.extensions    = ['ext/yab62/extconf.rb']

  gem.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  gem.files         = `git ls-files`.split("\n")
  gem.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  gem.name          = "yab62"
  gem.require_paths = ["lib"]
  gem.version       = YAB62::VERSION
end
