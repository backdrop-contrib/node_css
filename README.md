# Node CSS Module

The **Node CSS** module for Backdrop CMS allows administrators to add custom CSS styles to individual nodes selectively based on content type. This module is perfect for users who want custom styling for specific node types without affecting the entire site.

## Features

- Add custom CSS directly to node forms.
- Enable or disable custom CSS for individual content types.
- CSS is added inline to the head of the page, applying only to specific nodes.

## Installation

1. Download and place the `node_css` module in your Backdrop `modules` directory, typically found in `sites/all/modules`.
2. Go to `Admin > Functionality > Modules` in your Backdrop site.
3. Enable the **Node CSS** module.

## Configuration

1. Navigate to `Admin > Configuration > Content > Node CSS` to access the settings page.
2. You will see a list of all content types as checkboxes. Select the content types you want the **Node CSS** functionality to be active for.
3. Save your settings.

## Usage

1. After enabling **Node CSS** for a content type, go to the node edit form for a node of that type.
2. You will see a **Custom CSS** textarea field at the top of the form.
3. Enter your custom CSS for that node, then save the node.
4. The CSS will be added inline to the head of the node’s page, applying only to that specific node.

## Example

If you want to add a custom background color to a specific node of an enabled content type, add the following CSS to the **Custom CSS** field:

```css
body {
  background-color:  red !important;
}
```
This will apply a red background only to that specific node page.

## Troubleshooting

CSS may not apply as expected if there are conflicting styles or higher specificity from other stylesheets.

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/node_css/issues.

## Maintainers

This module is maintained by [Alan Mels](https://github.com/alanmels) of [AltaGrade.com](https://www.altagrade.com) and is open to contributions. Please feel free to submit issues and feature requests.

## Credits

This module was inspired by the [CSS Injector](https://github.com/backdrop-contrib/css_injector) module but designed with simplicity in mind to meet a specific need: allowing custom CSS rules directly on the node edit page, without the additional complexity of site-wide CSS management. We borrowed the CSS syntax highlighter from **CSS Injector** to enhance the editing experience.

