#!/usr/bin/env rake
require "bundler/gem_tasks"

task :default => :test

require 'rake/testtask'
Rake::TestTask.new(:test) do |test|
  test.libs << '.'
  test.pattern = 'test/test_*.rb'
  test.verbose = true
end
