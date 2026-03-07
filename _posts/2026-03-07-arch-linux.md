\---
title: Arch Linux Setup
date: 2026-03-07
\---

iwctl
station wlan0 connect "wifi-name"


sudo ln -sf /usr/bin/nvim /usr/bin/vi
sudo ln -sf /usr/bin/nvim /usr/bin/vim

set -U fish_greeting

sudo pacman -S \
amd-ucode \ 
pavucontrol \
sudo \
neovim
wayland \ 
pipewire wireplumber \
sudo \
git \
fish \
kitty \ 
wofi \ 
waybar \ 
hyprpaper \ 
hyprlock \ 
hypridle \
mako \
wl-clipboard \
hyprpolkitagent \
udiskie \
keyd \
firefox \
yazi \
xdg-desktop-portal-hyprland \ 
tlp \
mesa \
vulkan-radeon

noto-fonts noto-fonts-cjk noto-fonts-emoji


echo "nagisa ALL=(ALL) NOPASSWD:NOPASSWD:ALL" >> /etc/sudoers


systemctl --user enable --now pipewire wireplumber

sudo systemctl enable --now NetworkManager

tlp

keyd

sudo systemctl enable --now keyd


- sudo nano /etc/keyd/default.conf

```
[ids]
*
[main]
backspace = backslash
backslash = backspace
capslock = leftcontrol
grave = escape
delete = grave
```

sudo systemctl restart keyd

nmcli device wifi list

nmcli device wifi connect "wifi-name" password "pwd"



![wallpaper](/assets/img/posts/arch-linux/bloodborne.jpg)