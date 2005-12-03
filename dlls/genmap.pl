#!/usr/bin/perl

print "{\n\tglobal:\n\t\tGiveFnptrsToDll;\n\t\tGetEntityAPI;\n\t\tGetEntityAPI2;\n\t\tServer_GetBlendingInterface;\n";
while(<STDIN>) {
	chomp;
	/\( *(.*),/;
	print "\t\t" . $1 . ";\n";
}
print "\tlocal: *;\n};\n"
