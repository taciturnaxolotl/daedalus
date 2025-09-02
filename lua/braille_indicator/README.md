# Braille Typing Indicator Plugin for Neovim

A simple plugin that displays a random Braille character in your statusline that changes every time you type.

## Installation

### Using a plugin manager (recommended)

#### [packer.nvim](https://github.com/wbthomason/packer.nvim)

```lua
use {
  'taciturnaxolotl/daedalus',
  config = function()
    require('braille_indicator').setup()
  end
}
```

#### [lazy.nvim](https://github.com/folke/lazy.nvim)

```lua
{
  'taciturnaxolotl/daedalus',
  config = function()
    require('braille_indicator').setup()
  end
}
```

### Manual installation

1. Clone this repository to your Neovim configuration directory:

   ```
   git clone https://github.com/taciturnaxolotl/daedalus.git ~/.config/nvim/pack/plugins/start/daedalus
   ```

2. Add the following to your `init.lua`:
   ```lua
   require('braille_indicator').setup()
   ```

## Configuration

The plugin works with minimal configuration, but you can customize it:

```lua
require('braille_indicator').setup({
  update_statusline = true,  -- Automatically update the statusline
  verbose = true,            -- Show setup messages
})
```

### Adding to your statusline

If you're using a custom statusline setup, add the Braille indicator with:

```lua
%{v:lua.getBrailleIndicator()}
```

For example, with lualine:

```lua
require('lualine').setup({
  sections = {
    lualine_a = {
      function()
        return getBrailleIndicator()
      end,
      'mode'
    },
    -- other sections...
  }
})
```

