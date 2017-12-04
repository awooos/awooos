#!/usr/bin/env ruby

require 'open3'

class Qemu
  def call(platform:, memory:, args: [], &block)
    qemu = find_qemu(platform)
    command = [qemu, *args]

    Open3.popen3(command, &block)
  end

  def find_qemu(platform)
    "qemu-system-#{platform}"
  end


  def close
    Process.kill("KILL", wait_thr.pid)
  end
end

class QemuTest < Qemu
  def initialize(platform:, memory:, name:)
    @platform   = platform
    @memory     = memory
    @name       = name

    iso = find_iso(name, platform)

    @args = ["-m", memory, "-usb", "-serial", "stdio", "-name", name,
            "-monitor", "null", "-no-reboot", "-nographic", "-cdrom", iso]
  end

  def call
    stdout, stderr = Qemu.call(platform: @platform, memory: @memory,
                                args: args, &method(:collect_out_err))

    Results.new(stdout, stderr)
  end

  private

  def find_iso(name, platform)
    "iso/#{name}-#{platform}.iso"
  end

  def collect_out_err(stdin, stdout, stderr, wait_thr)
    stdin.close
    stdout = stdout.read
    stderr = stderr.read
    stdout.close
    stderr.close
  end

  class Results
    def initialize(stdout, stderr)
      @stdout = stdout
      @stderr = stderr
    end

    def print
      puts "TODO"
    end

    def status
      @results.values.all?
    end
  end
end

QemuTest.call(platform: 'i386', memory: '32M', name: 'awoo')
