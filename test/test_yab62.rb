# coding: utf-8

require 'test/unit'
require File.dirname(__FILE__) + "/../lib/yab62"

class TestYAB62 < Test::Unit::TestCase

  include YAB62
  
  def test_fixnum_becomes_string
    assert_kind_of String, 45.encode62
  end
  
  def test_bignum_becomes_string
    assert_kind_of String, 231087934571049032.encode62
  end
  
  def test_string_becomes_bignum
    assert_kind_of Bignum, 'aHealk43JZy'.decode62
  end
  
  def test_string_becomes_fixnum
    assert_kind_of Fixnum, 'j'.decode62
  end
  

  def test_edge_62_to_the_0_convertions_should_be_valid
    (0...62).each do |i|
      encode = i.encode62
      decode = encode.decode62
      assert_equal i, decode, "integer #{i.inspect} was encoded as #{encode.inspect} and was decoded to #{decode.inspect}"
    end
  end

  def test_edge_62_to_the_n_convertions_should_be_valid
    (0...3).each do |p|
      n = 62 ** p
      (0...62).each do |i|
        encode = (i+n).encode62
        decode = encode.decode62
        assert_equal i+n, decode, "interger #{i+n} was encoded as #{encode} and was decoded to #{decode}"
      end
    end
  end
end
