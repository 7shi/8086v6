let hshsiz = 1553
for quot in 1 .. hshsiz - 1 do
    let hshtab = Array.zeroCreate<bool> hshsiz
    let mutable count, idx = 0, 0
    while count < hshsiz do
        idx <- idx - quot
        if idx < 0 then idx <- idx + hshsiz
        if hshtab.[idx] then
            printfn "NG: quot = %d" quot
            exit 1
        hshtab.[idx] <- true
        count <- count + 1
    printfn "OK: quot = %d" quot
