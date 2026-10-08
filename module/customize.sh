#!/system/bin/sh

if [ "$(getprop ro.product.device)" != "Pong" ]; then
	ui_print "This module is for Nothing Phone 2 "
	ui_print "  What are you even trying to do "
	ui_print "  flashing it on a different device "
	abort
fi

chmod +x "$MODPATH/loader"
if OP=$("$MODPATH"/loader 2>&1); then
	ui_print "$OP"
else
	abort "Error: $OP"
fi
