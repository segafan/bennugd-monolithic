@echo off
echo rebuilding dcbs...
for /R . %%i in (*.prg) do bgdc.exe %%i
echo copying...
copy *.dcb "C:\Users\danielt3\code\bennugd-monolithic-PSP-dev\examples\dcbs"
pause


rem http://www.livrariacultura.com.br/scripts/musica/resenha/resenha.asp?nitem=17000645&sid=624971202121227717025234646&k5=1448B5B6&uid=

