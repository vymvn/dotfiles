---@type ChadrcConfig 
local M = {}

M.ui = {
    theme = 'catppuccin',
    transparency = true,
    theme_toggle = nil,

    statusline = {
        theme = "minimal", -- default/vscode/vscode_colored/minimal

        -- default/round/block/arrow (separators work only for "default" statusline theme;
        -- round and block will work for the minimal theme only)
        separator_style = "block",
        -- overriden_modules = nil,
    },

    nvdash = {
        load_on_startup = true
    },

    tabufline = {
        overriden_modules = function(modules)
            modules[4] = (function()
                return ""
            end)()

            -- or table.remove(modules, 4)
        end,
    },

}

M.plugins = 'custom.plugins'

return M
