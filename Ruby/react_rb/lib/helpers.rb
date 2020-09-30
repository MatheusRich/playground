def require_all(path)
  Dir[__dir__ + "/#{path}/*"].each &method(:require)
end
