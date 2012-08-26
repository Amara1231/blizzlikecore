<?php
/*
 * BCSoap client example
 *
 * a simple example how to invoke commands using SOAP
 */

$username = 'adm';
$password = 'adm';
$host = "127.0.0.1";
$soapport = 7878;
$command = "server info";

$client = new SoapClient(NULL,
array(
    "location" => "http://$host:$soapport/",
    "uri" => "urn:blizzlike",
    "style" => SOAP_RPC,
    'login' => $username,
    'password' => $password
));

try {
    $result = $client->executeCommand(new SoapParam($command, "command"));

    echo "Command succeeded! Output:<br />\n";
    echo $result;
}
catch (Exception $e)
{
    echo "Command failed! Reason:<br />\n";
    echo $e->getMessage();
}
?>
