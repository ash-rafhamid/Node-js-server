const e = require('express');
const express = require('express');
const app = express();
const port = 4001;
const notes = [];
let nextID = 1;

app.use(express.json());

app.get('/',(req,res)=>{
    res.send('hey im running a server')
})

app.get('/notes',(req,res)=>{
    res.json(notes )
})


app.get('/notes/:id',(req,res)=>{
    const note = notes.find(n=>n.id ===parseInt(req.params.id));
    if(!note){
        return res.status(404).json({error: 'Note not found'});
    }

    res.json(note);
})



app.post('/notes',(req,res)=>{

    const {title, body} = req.body;

    if(!title || !body){
        return res.status(400).json({error: 'Title and body are required'});
    }

    const newNote = {
        id : nextID++,
        title,
        body
    };

    notes.push(newNote);
    res.status(201).json(newNote);

});



app.listen(port ,()=>{
    console.log(`server is running on port ${port}`)
})