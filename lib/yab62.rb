require "yab62/version"
require "yab62/yab62"

class Integer
  def encode62
    YAB62.encode62(self)
  end
end

class String
  def decode62
    YAB62.decode62(self)
  end
end
