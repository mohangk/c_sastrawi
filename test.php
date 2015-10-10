<?php
$plural = "malikat-malaikat-nya";
preg_match('/^(.*)-(.*)$/', $plural, $words);

if (!isset($words[1]) || !isset($words[2])) {
    return $plural;
}

// malaikat-malaikat-nya -> malaikat malaikat-nya
print_r($words);
$suffix = $words[2];
if (in_array($suffix, array('ku', 'mu', 'nya', 'lah', 'kah', 'tah', 'pun')) &&
    preg_match('/^(.*)-(.*)$/', $words[1], $words)) {
    $words[2] .= '-' . $suffix;
}

print "blah \n";
print_r($words);
print "blah2 \n";
