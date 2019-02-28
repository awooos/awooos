#!/usr/bin/env ruby

require 'okay/http'
require 'nokogiri'

NAME_WIDTH=20
NUM_WIDTH=3

puts "#ifndef ALI__ERNO_H"
puts "#define ALI__ERNO_H"
puts

doc = Nokogiri::HTML(Okay::HTTP.get("https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html").body)
puts doc.
  xpath('//dl').xpath('dd | dt')
  .each_slice(2)
  .map { |x| [x[0].text[1..-2], x[1].text] }
  .each_with_index.map {|(name, comment), idx| [name.ljust(20), (idx + 1).to_s.ljust(3), comment] }
  .map { |name, idx, comment| [name, idx, comment.sub(/^\[OB XSR\]  /, '').strip] }
  .map { |name, idx, comment| "#define #{name} #{idx} // #{comment}" }

puts
puts "#endif"
