package main

import (
	"fmt"
)

type Batter interface {
	Hit(bases int)
	Score(runs int)
}

type Fielder interface {
	Catch(outs int)
}

type Pitcher interface {
	Walk(balls, strikes int)
}

type TwoWayPitcher struct {
	Name string
}

type OneWayPitcher struct {
	Name string
}

type TwoWayFielder struct {
	Name     string
	Position int
}

/* A TwoWayFielder implements the Fielder and Batter interface.
 */
func (fielder TwoWayFielder) Catch(outs int) {
	fmt.Printf("%s made %d outs.\n", fielder.Name, outs)
}

func (fielder TwoWayFielder) Hit(bases int) {
	fmt.Printf("%s had a hit worth %d bases.\n", fielder.Name, bases)
}

func (fielder TwoWayFielder) Score(runs int) {
	fmt.Printf("%s scored %d runs.\n", fielder.Name, runs)
}

/* A TwoWayPitcher implements the Pitcher and Batter interface.
 */
func (fielder TwoWayPitcher) Walk(balls, strikes int) {
	fmt.Printf("%s walked a batter on %d balls and %d strikes.\n", fielder.Name, balls, strikes)
}

func (fielder TwoWayPitcher) Hit(bases int) {
	fmt.Printf("(a pitcher) %s had a hit worth %d bases.\n", fielder.Name, bases)
}

func (fielder TwoWayPitcher) Score(runs int) {
	fmt.Printf("(a pitcher) %s scored %d runs.\n", fielder.Name, runs)
}

/* A OneWayPitcher implements the Pitcher interface.
 */
func (fielder OneWayPitcher) Walk(balls, strikes int) {
	fmt.Printf("%s walked a batter on %d balls and %d strikes.\n", fielder.Name, balls, strikes)
}

func AtBat(batter Batter) {
	batter.Score(2)
}
func PlayTheField(fielder Fielder) {
	fielder.Catch(2)
}
func Ace(pitcher OneWayPitcher) {
	pitcher.Walk(4, 2)
}

func main() {
	shohei_otani := TwoWayPitcher{"Shohei Otani"}
	aaron_judge := TwoWayFielder{"Aaron Judge", 6}

	AtBat(aaron_judge)
	Ace(OneWayPitcher(shohei_otani))
}
