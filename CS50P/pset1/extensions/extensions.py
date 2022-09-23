userInput = input("File name: ").strip().lower()

if "." in userInput:
    splitInput = userInput.split(".")
    finalSufixLocation = len(splitInput) - 1
    inputSufix = splitInput[finalSufixLocation]

    if inputSufix == "gif":
        print("image/gif")
    elif inputSufix == "jpg" or inputSufix == "jpeg":
        print("image/jpeg")
    elif inputSufix == "png":
        print("image/png")
    elif inputSufix == "pdf":
        print("application/pdf")
    elif inputSufix == "txt":
        print("text/plain")
    elif inputSufix == "zip":
        print("application/zip")
    else:
        print("application/octet-stream")
else:
    print("application/octet-stream")