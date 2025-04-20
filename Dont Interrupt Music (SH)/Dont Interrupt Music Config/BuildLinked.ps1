# Set Working Directory
Split-Path $MyInvocation.MyCommand.Path | Push-Location
[Environment]::CurrentDirectory = $PWD

Remove-Item "$env:RELOADEDIIMODS/Dont_Interrupt_Music_Config/*" -Force -Recurse
dotnet publish "./Dont_Interrupt_Music_Config.csproj" -c Release -o "$env:RELOADEDIIMODS/Dont_Interrupt_Music_Config" /p:OutputPath="./bin/Release" /p:ReloadedILLink="true"

# Restore Working Directory
Pop-Location