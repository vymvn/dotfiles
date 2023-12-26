local plugins = {

    {
        'postfen/clipboard-image.nvim',
        lazy = false,
        config = function ()
            require "custom.configs.clipboard-image"
        end
    },
    {
        "neovim/nvim-lspconfig",
        config = function ()
           require "plugins.configs.lspconfig"
           require "custom.configs.lspconfig"
        end
    },
    {
        'lervag/vimtex',
        lazy = false,
        config = function ()
            require "custom.configs.vimtex"
        end
    },
    {
        'andweeb/presence.nvim',
        lazy = false,
        config = function ()
            require "custom.configs.presence"
        end
    },
    {
        "iamcco/markdown-preview.nvim",
        cmd = { "MarkdownPreviewToggle", "MarkdownPreview", "MarkdownPreviewStop" },
        ft = { "markdown" },
        build = function() vim.fn["mkdp#util#install"]() end,
    }
}

return plugins
