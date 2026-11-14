# My Stylist (prototype)

A small C console program exploring the core idea behind "My Stylist",
a planned AI app that suggests outfits only from clothes you already own.

## What this prototype does
- Holds a sample wardrobe (tops, bottoms, dresses)
- Asks for an occasion (casual, office, party)
- Scores outfit combinations and prints the top 3 looks, each with a hairstyle and accessory suggestion

## What it does NOT do (yet)
- No photos, and no body type, skin tone or face analysis
- No real AI: the suggestions come from fixed rules

## The full vision
Users upload a full-body photo and photos of their own clothes. The app
saves their wardrobe and gives three complete looks per occasion, including
hairstyle and accessories, shown on the user's own photo.

## How to run
    gcc stylist.c -o stylist
    ./stylist
