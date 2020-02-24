#!/usr/bin/perl

print "VERS_1.1 {\n\tglobal:\n\t\tGiveFnptrsToDll;\n\t\tGetEntityAPI;\n\t\tGetEntityAPI2;\n\t\tServer_GetBlendingInterface;\n";
while(<STDIN>) {
	chomp;
	/\( *(.*),/;
	print "\t\t" . $1 . ";\n";
}
print "\tlocal: *;\n};\n"
