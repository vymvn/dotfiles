require'clipboard-image'.setup {

    default = {
        -- img_dir = { "%:p:h", "img", "%:t:r" },
        img_dir = { "%:p:h", "img" },
        img_name = function ()
            vim.fn.inputsave()
            local name = vim.fn.input('Name: ')
            vim.fn.inputrestore()

            if name == nil or name == '' then
                return os.date('%y-%m-%d-%H-%M-%S')
            end
            return name
        end,
    },
}

vim.keymap.set({ 'n', 'v' }, '<leader>pi', '<cmd>PasteImg<CR>', { desc = 'Paste image' })
-- vim.keymap.set({ 'n', 'v' }, '<leader><C-v>', '<cmd>PasteImg<CR>')

