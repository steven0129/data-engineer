const express = require('express')
const execFile = require('child_process').execFile
const path = require('path')

const app = express()
const PORT = 3000

app.use((req, res, next) => {
    res.header("Access-Control-Allow-Origin", "*")
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept")
    next()
})

app.get('/data', (req, res) => {
    execFile('./a.out', [req.query.q], (err, stdout, stderr) => {
        if(err) {
            console.error('stderr', stderr)
        }

        console.log(`GET: ${req.query.q}`)
        res.send(stdout)
    })
})

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname + '/index.html'))
})

app.listen(PORT, () => console.log(`Listening on port ${PORT}...`))