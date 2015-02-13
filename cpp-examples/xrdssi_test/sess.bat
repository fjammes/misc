session /tmp/3
send echo 3foobar
session /tmp/2
send echo 2foobar
session /tmp/1
send echo 1foobar
session /tmp/2
unprovision
session /tmp/1
unprovision
