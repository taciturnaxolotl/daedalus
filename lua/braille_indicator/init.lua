-- Braille Typing Indicator Plugin for Neovim
-- This is a proper plugin structure for installation in your Neovim config

local M = {}

-- Braille unicode characters (⠀ to ⣿)
local brailleChars = {
  '⠀', '⠁', '⠂', '⠃', '⠄', '⠅', '⠆', '⠇', '⠈', '⠉', '⠊', '⠋', '⠌', '⠍', '⠎', '⠏',
  '⠐', '⠑', '⠒', '⠓', '⠔', '⠕', '⠖', '⠗', '⠘', '⠙', '⠚', '⠛', '⠜', '⠝', '⠞', '⠟',
  '⠠', '⠡', '⠢', '⠣', '⠤', '⠥', '⠦', '⠧', '⠨', '⠩', '⠪', '⠫', '⠬', '⠭', '⠮', '⠯',
  '⠰', '⠱', '⠲', '⠳', '⠴', '⠵', '⠶', '⠷', '⠸', '⠹', '⠺', '⠻', '⠼', '⠽', '⠾', '⠿',
  '⡀', '⡁', '⡂', '⡃', '⡄', '⡅', '⡆', '⡇', '⡈', '⡉', '⡊', '⡋', '⡌', '⡍', '⡎', '⡏',
  '⡐', '⡑', '⡒', '⡓', '⡔', '⡕', '⡖', '⡗', '⡘', '⡙', '⡚', '⡛', '⡜', '⡝', '⡞', '⡟',
  '⡠', '⡡', '⡢', '⡣', '⡤', '⡥', '⡦', '⡧', '⡨', '⡩', '⡪', '⡫', '⡬', '⡭', '⡮', '⡯',
  '⡰', '⡱', '⡲', '⡳', '⡴', '⡵', '⡶', '⡷', '⡸', '⡹', '⡺', '⡻', '⡼', '⡽', '⡾', '⡿',
  '⢀', '⢁', '⢂', '⢃', '⢄', '⢅', '⢆', '⢇', '⢈', '⢉', '⢊', '⢋', '⢌', '⢍', '⢎', '⢏',
  '⢐', '⢑', '⢒', '⢓', '⢔', '⢕', '⢖', '⢗', '⢘', '⢙', '⢚', '⢛', '⢜', '⢝', '⢞', '⢟',
  '⢠', '⢡', '⢢', '⢣', '⢤', '⢥', '⢦', '⢧', '⢨', '⢩', '⢪', '⢫', '⢬', '⢭', '⢮', '⢯',
  '⢰', '⢱', '⢲', '⢳', '⢴', '⢵', '⢶', '⢷', '⢸', '⢹', '⢺', '⢻', '⢼', '⢽', '⢾', '⢿',
  '⣀', '⣁', '⣂', '⣃', '⣄', '⣅', '⣆', '⣇', '⣈', '⣉', '⣊', '⣋', '⣌', '⣍', '⣎', '⣏',
  '⣐', '⣑', '⣒', '⣓', '⣔', '⣕', '⣖', '⣗', '⣘', '⣙', '⣚', '⣛', '⣜', '⣝', '⣞', '⣟',
  '⣠', '⣡', '⣢', '⣣', '⣤', '⣥', '⣦', '⣧', '⣨', '⣩', '⣪', '⣫', '⣬', '⣭', '⣮', '⣯',
  '⣰', '⣱', '⣲', '⣳', '⣴', '⣵', '⣶', '⣷', '⣸', '⣹', '⣺', '⣻', '⣼', '⣽', '⣾', '⣿'
}

-- Current braille character
local currentBraille = brailleChars[1]

-- Update braille character randomly
local function updateBrailleChar()
  -- Use os.time() for randomness
  math.randomseed(os.time() * 1000 + os.clock() * 10000)
  local idx = math.random(1, #brailleChars)
  currentBraille = brailleChars[idx]
  return currentBraille
end

-- Get current braille character for statusline
function M.getBrailleIndicator()
  return currentBraille
end

-- Setup function with options
function M.setup(opts)
  opts = opts or {}
  
  -- Make sure statusline is visible
  vim.o.laststatus = 2
  
  -- Key press handler
  local function onKeyPress()
    -- Update braille character
    updateBrailleChar()
  end
  
  -- Set up autocommands
  vim.api.nvim_create_autocmd({"InsertCharPre", "CursorMovedI"}, {
    callback = onKeyPress,
    group = vim.api.nvim_create_augroup("BrailleIndicator", { clear = true })
  })
  
  -- Make the function available globally for statusline
  _G.getBrailleIndicator = M.getBrailleIndicator
  
  -- Add to statusline if requested
  if opts.update_statusline then
    vim.o.statusline = "%{v:lua.getBrailleIndicator()} %f %m %r %= %l,%c "
  end
  
  -- Print setup message
  if opts.verbose then
    print("Braille indicator active. The character will change as you type.")
    print("Add %{v:lua.getBrailleIndicator()} to your statusline if not already there.")
  end
end

return M