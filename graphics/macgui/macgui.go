package main

import (
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/container"
	"fyne.io/fyne/v2/widget"
	"image/color"
)

func example1() {
	a := app.New()

	w := a.NewWindow("Hello, Fyne!")
	w.SetContent(canvas.NewText("Hello, Fyne!", color.White))
	w.ShowAndRun()
}

func example2() {
	a := app.New()
	w := a.NewWindow("Hello")

	hello := widget.NewLabel("Hello Fyne!")
	w.SetContent(container.NewVBox(
		hello,
		widget.NewButton("Hi!", func() {
			hello.SetText("Welcome :)")
		}),
	))

	w.ShowAndRun()
}

func main() {
	//example1()
	example2()
}
